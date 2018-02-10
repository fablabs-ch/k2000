<template>
  <v-list-tile avatar>
    <v-list-tile-action>
      <v-select
        :items="['ALCOHOL', 'MINERAL', 'SIRUP', 'OTHER']"
        v-model="value.type"
        max-height="auto"
        @change="changed"
      >
        <template slot="selection" slot-scope="data">
          <ingredient-type :type="data.item"></ingredient-type>
        </template>
        <template slot="item" slot-scope="data">
          <ingredient-type :type="data.item" label></ingredient-type>
        </template>
    </v-select>
    </v-list-tile-action>
    <v-list-tile-content>
      <v-text-field name="name" placeholder="Name"
      v-model="value.name" @change="changed"
      :rules="[() => value.name.length > 0 || 'A name is required']"
      required></v-text-field>
    </v-list-tile-content>
    <v-list-tile-action>
      <color-picker v-model="value.color" @input="changed"></color-picker>
      <v-btn icon @click.native="deleted" v-if="canDelete">X</v-btn>
    </v-list-tile-action>
  </v-list-tile>
</template>

<script>
import IngredientType from '@/components/IngredientType'
import ColorPicker from '@/components/ColorPicker'

export default {
  props: ['value', 'canDelete'],
  data () {
    return {
    }
  },
  methods: {
    changed () {
      this.$emit('change', this.value)
    },
    deleted () {
      this.$emit('delete', this.value)
    }
  },
  components: {
    IngredientType,
    ColorPicker
  }
}
</script>

<style>

</style>
