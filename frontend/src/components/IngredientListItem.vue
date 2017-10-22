<template>
  <v-list-tile>
    <v-list-tile-action>
      <v-select
        label="Type"
        :items="['ALCOOL', 'MINERAL', 'SIRUP', 'OTHER']"
        v-model="value.type"
        max-height="auto"
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
      <v-text-field name="name" label="Name" v-model="value.name"></v-text-field>
    </v-list-tile-content>
    <v-list-tile-action>
      <color-picker v-model="value.color"></color-picker>
    </v-list-tile-action>
  </v-list-tile>
</template>

<script>
import IngredientType from '@/components/IngredientType'
import ColorPicker from '@/components/ColorPicker'

export default {
  props: ['value'],
  data () {
    return {
      e11: 'MINERAL',
      color: '#ff0000'
    }
  },
  methods: {
    save () {
      // TODO save / new ?
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
