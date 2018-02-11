<template>
  <v-container>
    <v-layout row>
      <v-flex xs2>
        <v-text-field required name="mm" label="mm" v-model="value.valveDistanceMm" type="number" @change="changed"></v-text-field>
      </v-flex>
      <v-flex xs3>
        <v-text-field required name="valveId" label="valveId" v-model="value.valveId" type="text" @change="changed"></v-text-field>
      </v-flex>
      <v-flex xs6>
        <v-select
              :items="ingredients"
              v-model="value.ingredientId"
              item-value="id"
              item-text="name"
              label="Ingredient"
              autocomplete
              single-line
              bottom
              required
              @change="changed"
            ></v-select>
      </v-flex>
      <v-flex xs1>
        <v-btn icon @click.native="deleted" v-if="canDelete">X</v-btn>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
export default {
  name: 'ingredientConfig',
  props: ['value', 'canDelete'],
  computed: {
    ingredients () {
      return Object.values(this.$root.ingredients)
    }
  },
  methods: {
    changed () {
      this.$emit('change', this.value)
    },
    deleted () {
      this.$emit('delete', this.value)
    }
  }
}
</script>

<style>
</style>
